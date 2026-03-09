from django.contrib import admin
from .models import *

# Register your models here.
@admin.register(Supplement)
class SupplementAdmin(admin.ModelAdmin):
    list_display = ["name", "company", "description", "category", "user"]
    exclude = ("user",)

    def save_model(self, request, obj, form, change):
        obj.user = request.user
        return super(SupplementAdmin, self).save_model(request, obj, form, change)


@admin.register(Category)
class CategoryAdmin(admin.ModelAdmin):
    list_display = ["name", "description", "isActive"]

@admin.register(Company)
class CompanyAdmin(admin.ModelAdmin):
    list_display = ["name", "originDate", "size"]