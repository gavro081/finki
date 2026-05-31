from django import forms
from .models import Exhibition

class ExhibitionForm(forms.ModelForm):
    def __init__(self, *args, **kwargs):
        super(ExhibitionForm, self).__init__(*args, **kwargs)
        for name, field in self.fields.items():
            field.widget.attrs['class'] = 'form-control rounded-pill'
            field.widget.attrs['placeholder'] = name.replace('_', ' ').capitalize()
            field.label = ''

    class Meta:
        model = Exhibition
        fields = ['title', 'start_date', 'end_date', 'location', 'description']