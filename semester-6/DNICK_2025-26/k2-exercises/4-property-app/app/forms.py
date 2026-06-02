from django import forms
from .models import Property

class PropertyForm(forms.ModelForm):
   def __init__(self, *args, **kwargs):
       super(PropertyForm, self).__init__(*args, **kwargs)
       for field_name, field in self.fields.items():
           if field_name not in ['is_reserved', 'is_sold']:
               field.widget.attrs['class'] = 'form-control'


   class Meta:
       model = Property
       exclude = ['publish_date', "price"]