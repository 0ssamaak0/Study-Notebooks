import torch
from torch import nn, optim

Dims = [28 * 28, 128, 64, 36, 18, 2]
# AE Model
class LinearAE(nn.Module):
    def __init__(self):
        """Initialize the Autoencoder."""
        super().__init__()
        encoder_layers = [nn.Linear(Dims[i], Dims[i + 1]) for i in range(len(Dims) - 1)]
        # Add ReLU activation to each layer except the last
        encoder_layers = [layer for layer in encoder_layers for layer in (layer, nn.ReLU())][:-1]
        self.encoder = nn.Sequential(*encoder_layers)
        decoder_layers = [nn.Linear(Dims[i], Dims[i - 1]) for i in range(len(Dims) - 1, 0, -1)]
        # Add ReLU activation to each layer except the last
        decoder_layers = [layer for layer in decoder_layers for layer in (layer, nn.ReLU())][:-1]
        self.decoder = nn.Sequential(*decoder_layers)

    
    def forward(self, x):
        """Forward pass through the autoencoder."""
        x = x.view(x.size(0), -1)  # Flatten the input
        encoded = self.encoder(x)
        decoded = self.decoder(encoded)
        decoded = nn.functional.sigmoid(decoded)
        return decoded
    
class ConvAE(nn.Module):
    def __init__(self, use_skip: bool = False):
        """Initialize the Convolutional Autoencoder with optional skip connections."""
        super().__init__()
        self.use_skip = use_skip

        # Encoder layers
        self.conv1 = nn.Conv2d(1,  32, kernel_size=3, padding=1)  # -> (batch,32,28,28)
        self.relu1 = nn.ReLU()
        self.pool1 = nn.MaxPool2d(2, 2)                           # -> (batch,32,14,14)

        self.conv2 = nn.Conv2d(32, 16, kernel_size=3, padding=1)  # -> (batch,16,14,14)
        self.relu2 = nn.ReLU()
        self.pool2 = nn.MaxPool2d(2, 2)                           # -> (batch,16,7,7)

        self.conv3 = nn.Conv2d(16, 8, kernel_size=3, padding=1)   # -> (batch,8,7,7)
        self.relu3 = nn.ReLU()

        # Decoder layers
        self.up1    = nn.Upsample(scale_factor=2, mode='nearest') # -> (batch,8,14,14)
        self.deconv1 = nn.Conv2d(8, 16, kernel_size=3, padding=1) # -> (batch,16,14,14)
        self.relu4   = nn.ReLU()

        self.up2    = nn.Upsample(scale_factor=2, mode='nearest') # -> (batch,16,28,28)
        self.deconv2 = nn.Conv2d(16, 32, kernel_size=3, padding=1)# -> (batch,32,28,28)
        self.relu5   = nn.ReLU()

        self.deconv3 = nn.Conv2d(32, 1, kernel_size=3, padding=1) # -> (batch,1,28,28)
        self.sigmoid = nn.Sigmoid()

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        """Forward pass with optional skip connections."""
        # Encoder
        x1 = self.relu1(self.conv1(x))    # (32,28,28)
        x1p = self.pool1(x1)              # (32,14,14)

        x2 = self.relu2(self.conv2(x1p))  # (16,14,14)
        x2p = self.pool2(x2)              # (16,7,7)

        z  = self.relu3(self.conv3(x2p))  # (8,7,7)

        # Decoder
        y = self.up1(z)                   # (8,14,14)
        y = self.relu4(self.deconv1(y))   # (16,14,14)
        if self.use_skip:
            y = y + x2                    # skip connection from conv2 output

        y = self.up2(y)                   # (16,28,28)
        y = self.relu5(self.deconv2(y))   # (32,28,28)
        if self.use_skip:
            y = y + x1                    # skip connection from conv1 output

        y = self.deconv3(y)               # (1,28,28)
        return self.sigmoid(y)

    def decode(self, z: torch.Tensor) -> torch.Tensor:
        """
        Decode a latent tensor z into an image. 
        Note: only works when use_skip=False (skip connections disabled).
        """
        # Upsample and decode without skips
        y = self.up1(z)
        y = self.relu4(self.deconv1(y))
        y = self.up2(y)
        y = self.relu5(self.deconv2(y))
        y = self.deconv3(y)
        return self.sigmoid(y)