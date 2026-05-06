from django.db import models

# Create your models here.
# Секој филм се карактеризира со наслов, постер (слика), ИМДБ код, година на издавање, продукциска куќа,
# траење (во минути), жанр (акција, комедија, драма, хорор, sci-fi,
# документарец, анимација), формат (дигитален, Blu-ray, DVD) и цена на rental

# име, земја и град во кој се наоѓа, година на основање и официјален вебсајт.
class Publisher(models.Model):
    title = models.CharField()
    country = models.CharField()
    year_origin = models.IntegerField()
    city = models.CharField()
    website_link = models.CharField()

    def __str__(self):
        return self.title

class Movie(models.Model):
    GENRE_TYPE = (
        ("A", "Action"),
        ("c", "Comedy"),
        ("D", "Drama"),
        ("h", "Horror"),
        ("s", "Sci-fi"),
        ("d", "Documentary"),
        ("a", "Animation"),
    )
    FORMAT_TYPE = (
        ("d", "Digital"),
        ("b", "Blu-ray"),
        ("D", "DVD"),
    )

    title = models.CharField()
    image = models.ImageField(upload_to="images/")
    imdb = models.CharField()
    year_release = models.IntegerField()
    publisher = models.ForeignKey(Publisher, on_delete=models.CASCADE)
    duration = models.IntegerField()
    genre = models.CharField(choices=GENRE_TYPE)
    format = models.CharField(choices=FORMAT_TYPE)
    cost = models.IntegerField()

    def __str__(self):
        return self.title
