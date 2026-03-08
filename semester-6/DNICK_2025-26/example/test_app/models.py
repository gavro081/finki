from django.core.exceptions import ValidationError
from django.db import models
from django.contrib.auth.models import User


# Create your models here.
class Product(models.Model):
    PRODUCT_TYPE = [
        ("T", "Technology"),
        ("F", "Food")
    ]
    name = models.CharField(max_length=64)
    price = models.FloatField()
    type = models.CharField(max_length=1, choices=PRODUCT_TYPE)

    def __str__(self):
        return f"{self.name} - {self.price} - {self.type}"

class Inventory(models.Model):
    product = models.OneToOneField(Product, on_delete=models.CASCADE)
    quantity = models.IntegerField(default=0)

    class Meta:
        verbose_name_plural = "Inventories"

    def __str__(self):
        return f"{self.product}: {self.quantity} items"


class Order(models.Model):
    product = models.ForeignKey(Product, on_delete=models.CASCADE)
    user = models.ForeignKey(User, on_delete=models.DO_NOTHING)
    time = models.DateTimeField()
    quantity = models.IntegerField()

    def save(self, *args, **kwargs):
        if not self.pk:
            inventory = self.product.inventory
            inventory.quantity -= self.quantity

            if inventory.quantity < 0:
                raise ValidationError("product is out of stock")
            inventory.save()

        super().save(*args, **kwargs)

    def __str__(self):
        return f"Order for {self.product} by {self.user.username}"


class Employee(models.Model):
    name = models.CharField(max_length=64)
    surname = models.CharField(max_length=64)
    user = models.ForeignKey(User, on_delete=models.DO_NOTHING)
    salary = models.FloatField()

    def __str__(self):
        return f"Employee - {self.name} {self.surname}"

