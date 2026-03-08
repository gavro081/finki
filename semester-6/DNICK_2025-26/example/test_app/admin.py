from django.contrib import admin
from .models import *

# Register your models here.
class ProductsAdmin(admin.ModelAdmin):
    list_display = ("name", "price", "type", "in_stock")
    list_filter = ["type"]

    def in_stock(self, obj):
        return obj.inventory.quantity

@admin.register(Inventory)
class InventoryAdmin(admin.ModelAdmin):
    list_display = ["product", "quantity"]

@admin.register(Employee)
class EmployeeAdmin(admin.ModelAdmin):
    list_display = ["name", "surname", "salary"]
    
@admin.register(Order)
class OrderAdmin(admin.ModelAdmin):
    list_display = ["product", "user", "time", "quantity"]

    def save_model(self, request, obj, form, change):
        print(f"example logging, obj = {obj}")
        super().save_model(request, obj, form, change)


admin.site.register(Product, ProductsAdmin)