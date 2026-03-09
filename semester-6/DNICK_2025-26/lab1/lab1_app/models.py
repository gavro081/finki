from django.db import models
from django.contrib.auth.models import User

# Create your models here.
# Секој суплемент се карактеризира со име, компанија производител опис и информација за тоа
# во која категорија припаѓа, корисникот кој го креирал продуктот, фотографија од продуктот,
# цена и количина. За секоја категорија се чува име, опис и дали е активна (bool).
# За секоја компанија производител се чува нејзино име, датум на основање и тип на компанија
# (мала, средна, голема). Сите модели треба да се регистрираат во админ панелот.
#
# При креирање на суплемент, корисникот се доделува автоматски според најавениот корисник.

class Category(models.Model):
    name = models.CharField()
    description = models.TextField()
    isActive = models.BooleanField(default=True)

    def __str__(self):
        return f"{self.name} - {self.isActive}"

class Company(models.Model):
    name = models.CharField()
    originDate = models.DateField()
    size = models.CharField(choices=[('s','SMALL'), ('m','MEDIUM'), ('b','BIG')])

    def __str__(self):
        return f"Company: {self.name}"

class Supplement(models.Model):
    name = models.CharField()
    company = models.ForeignKey(Company, on_delete=models.CASCADE)
    description = models.TextField()
    category = models.ForeignKey(Category, on_delete=models.CASCADE)
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    photo = models.ImageField(upload_to='images')
    price = models.FloatField()
    quantity = models.IntegerField()

    def __str__(self):
        return f"{self.name} - {self.category}"