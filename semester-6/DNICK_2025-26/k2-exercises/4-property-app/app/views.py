from django.db.models import Sum
from django.shortcuts import render, get_object_or_404, redirect
from .forms import PropertyForm
from .models import *
from django.db.models import Q
# Create your views here.
def index(request):
    properties = Property.objects.filter(Q(is_sold=False) & Q(area__gt=100))
    properties = properties.annotate(total_price=Sum('propertycharacteristics__characteristic__price'))
    context = {'properties': properties}
    return render(request, 'index.html', context)

def edit_property(request, pk):
    property = get_object_or_404(Property, pk=pk)
    if request.method == 'POST':
        form = PropertyForm(request.POST, request.FILES, instance=property)
        if form.is_valid():
            form.save()
            characteristics = request.POST.get('characteristics') or ''

            names = [c.strip() for c in characteristics.split(',') if c.strip()]

            PropertyCharacteristics.objects.filter(property=property).exclude(
                characteristic__name__in=names).delete()

            for name in names:
                char = Characteristic.objects.filter(name=name).first()
                if char is None:
                    continue
                PropertyCharacteristics.objects.get_or_create(
                    property=property, characteristic=char)

            return redirect('index')

    form = PropertyForm(instance=property)
    characteristics = PropertyCharacteristics.objects.filter(property=property)
    characteristics_str = ''
    for c in characteristics:
        characteristics_str += c.characteristic.name + ','

    characteristics_str = characteristics_str[:-1]
    context = {'form': form, 'property_id': pk, 'char_str': characteristics_str}
    return render(request, 'edit.html', context)