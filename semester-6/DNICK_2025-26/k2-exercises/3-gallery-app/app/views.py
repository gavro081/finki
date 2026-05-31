from django.shortcuts import render, redirect
from .forms import ExhibitionForm
from .models import Exhibition, Artwork
# Create your views here.
def index(request):
    exhibitions = Exhibition.objects.all()
    data = []
    for ex in exhibitions:
        artwork = Artwork.objects.filter(exhibition=ex).first()
        data.append({
            'exhibition': ex,
            'artwork': artwork
        })

    context = {'exhibition_data': data}
    return render(request, 'index.html', context)

def add_exhibition(request):
    if request.method == 'POST':
        form = ExhibitionForm(request.POST)
        if form.is_valid():
            exhibition = form.save(commit=False)
            exhibition.save()
            return redirect('index')

    form = ExhibitionForm()
    context = {'form': form}
    return render(request, 'add_exhibition.html', context)

