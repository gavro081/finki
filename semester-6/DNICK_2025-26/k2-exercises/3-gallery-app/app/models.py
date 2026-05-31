from django.db import models
from django.contrib.auth.models import User

# Create your models here.
class Artist(models.Model):
    ARTIST_STYLE = [
        ('impressionism', 'Impressionism'),
        ('pop art', 'Pop Art'),
        ('graffiti', 'Graffiti')
    ]
    user = models.OneToOneField(User, on_delete=models.CASCADE)
    name = models.CharField(max_length=100)
    surname = models.CharField(max_length=100)
    art_style = models.CharField(choices=ARTIST_STYLE)

    def __str__(self):
        return f"{self.name} {self.surname}"

class Exhibition(models.Model):
    title = models.CharField(max_length=100)
    start_date = models.DateField()
    end_date = models.DateField()
    description = models.CharField(max_length=100)
    location = models.CharField(max_length=100)

    def __str__(self):
        return self.title

class Artwork(models.Model):
    title = models.CharField(max_length=100)
    creation_date = models.DateField()
    image = models.ImageField(upload_to='artwork/', null=True, blank=True)
    artist = models.ForeignKey(Artist, on_delete=models.CASCADE)
    exhibition = models.ForeignKey(Exhibition, on_delete=models.CASCADE)

    def __str__(self):
        return self.title