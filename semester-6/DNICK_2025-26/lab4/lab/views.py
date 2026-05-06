from django.shortcuts import render
from .models import *

# Create your views here.
def index(request):
    movies = Movie.objects.all()
    length = len(movies)
    context = {'movies': movies, 'length': length}
    return render(request, 'index.html', context)

def movie_detail(request, pk):
    movie = Movie.objects.get(pk=pk)
    context = { "movie": movie }
    return render(request, 'movie_detail.html', context)