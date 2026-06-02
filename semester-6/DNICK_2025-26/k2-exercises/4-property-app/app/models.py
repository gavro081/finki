from django.contrib.auth.models import User
from django.db import models


# Create your models here.
class Property(models.Model):
    name = models.CharField(max_length=100)
    description = models.CharField(max_length=100)
    area = models.DecimalField(decimal_places=2,max_digits=7)
    publish_date = models.DateField()
    image = models.ImageField(upload_to='properties/', blank=True, null=True)
    is_reserved = models.BooleanField(default=False)
    is_sold = models.BooleanField(default=False)

    def __str__(self):
        return f'Property: {self.name} - {self.area} - {self.description}'

class Agent(models.Model):
    name = models.CharField(max_length=100)
    surname = models.CharField(max_length=100)
    number = models.CharField(max_length=20)
    link_social = models.CharField(max_length=100)
    num_sales = models.IntegerField(default=0)
    email = models.CharField(max_length=100)
    user = models.ForeignKey(User, on_delete=models.CASCADE)

    def __str__(self):
        return f'Agent: {self.name} {self.surname}'

class AgentProperties(models.Model):
    agent = models.ForeignKey(Agent, on_delete=models.CASCADE)
    property = models.ForeignKey(Property, on_delete=models.CASCADE)

    class Meta:
        unique_together = ('agent', 'property')

    def __str__(self):
        return f"{self.agent} - {self.property}"

class Characteristic(models.Model):
    name = models.CharField(max_length=100)
    price = models.IntegerField()

    def __str__(self):
        return f'Characteristic: {self.name} - {self.price}'

class PropertyCharacteristics(models.Model):
    property = models.ForeignKey(Property, on_delete=models.CASCADE)
    characteristic = models.ForeignKey(Characteristic, on_delete=models.CASCADE)

    class Meta:
        unique_together = ('property', 'characteristic')

    def __str__(self):
        return f"{self.property} - {self.characteristic}"