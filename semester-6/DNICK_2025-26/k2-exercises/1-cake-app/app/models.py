from django.core.exceptions import ValidationError
from django.db import models
from django.contrib.auth.models import User
from django.db.models import Sum
from openpyxl.styles.builtins import total


# Create your models here.

class Baker(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE)
    name = models.CharField(max_length=100)
    surname = models.CharField(max_length=100)
    phone = models.CharField(max_length=15)
    email = models.CharField(max_length=50)

    def __str__(self):
        return f"{self.name} {self.surname}"


class Cake(models.Model):
    name = models.CharField(max_length=100, unique=True) # dali unique=True e dovolno za da go zadovoli uslovot?
    price = models.DecimalField(decimal_places=2, max_digits=5)
    weight = models.IntegerField()
    description = models.CharField(max_length=200)
    image = models.ImageField(upload_to='cakes/', null=True, blank=True)
    baker = models.ForeignKey(Baker, on_delete=models.CASCADE)

    def __str__(self):
        return f"{self.name}"
