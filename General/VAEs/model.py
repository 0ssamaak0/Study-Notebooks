import torch
import torch.nn as nn

# Input img ➡️ hidden ➡️ mean, std ➡️ z ➡️ decoder ➡️ output img
class VAE(nn.Module):
    def __init__(self, input_dim, h_dim = 200, z_dim=20):
        super().__init__()
        # Encoder
        self.img2hid = nn.Linear(input_dim, h_dim)
        self.hid2mu = nn.Linear(h_dim, z_dim)
        self.hid2sigma = nn.Linear(h_dim, z_dim)
        # Decoder
        self.z2hid = nn.Linear(z_dim, h_dim)
        self.hid2img = nn.Linear(h_dim, input_dim)


    def encode(self, x):
        # q_phi(z|x)
        h = torch.relu(self.img2hid(x))
        mu, sigma = self.hid2mu(h), self.hid2sigma(h)
        return mu, sigma



    def decode(self, z):
        h = torch.relu(self.z2hid(z))
        image = torch.sigmoid(self.hid2img(h))
        return image

    def forward(self, x):
        mu, sigma = self.encode(x)
        std = torch.exp(0.5 *sigma)
        epsilon = torch.randn_like(sigma) # Random Gaussian Noise
        z_reparameterized = mu + sigma * epsilon
        x_reconstructed = self.decode(z_reparameterized)
        return x_reconstructed, mu, sigma # mu and sigma are used for loss calculation (KL divergence)
    
