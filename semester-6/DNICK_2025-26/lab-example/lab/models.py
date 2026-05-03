from django.db import models

class Publisher(models.Model):
    title = models.CharField()
    country = models.CharField()
    city = models.CharField()
    release_year = models.IntegerField()
    website = models.CharField()

    def __str__(self):
        return self.title

class Book(models.Model):
    COVER_TYPE = (
        ("H", "Hard Cover"),
        ("P", "Paperback")
    )

    CATEGORY_TYPE = (
        ("R", "Romance"),
        ("T", "Thriller"),
        ("B", "Biography"),
        ("C", "Classic"),
        ("D", "Drama"),
        ("H", "History"),
    )

    title = models.CharField()
    image = models.ImageField(upload_to="images/")
    isbn = models.CharField()
    release_year = models.IntegerField()
    num_pages = models.IntegerField()
    book_dimesions = models.CharField()
    cover_type = models.CharField(choices=COVER_TYPE)
    category_type = models.CharField(choices=CATEGORY_TYPE)
    publisher = models.ForeignKey(Publisher, on_delete=models.CASCADE)
    price = models.IntegerField()

    def __str__(self):
        return self.title
