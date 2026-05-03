from django.shortcuts import render, redirect
from .models import Book, Publisher
from .forms import BookForm

def index(request):
    books = Book.objects.all()
    context = {'books': books}
    return render(request, 'index.html', context)

def add_book(request):
    if request.method == 'POST':
        form = BookForm(request.POST, request.FILES)
        if form.is_valid():
            form.save()
            return redirect('index')
    else:
        form = BookForm()

    publishers = Publisher.objects.all()
    context = {'form': form, 'publishers': publishers}
    return render(request, 'add_book.html', context)


def book_detail(request, pk):
    book = Book.objects.get(pk=pk)
    context = { "book": book }
    return render(request, 'book_detail.html', context)
