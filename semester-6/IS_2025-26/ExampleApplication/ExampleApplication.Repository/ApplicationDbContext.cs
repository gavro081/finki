using ExampleApplication.Domain.Models;
using Microsoft.EntityFrameworkCore;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;

namespace ExampleApplication.Repository;

public class ApplicationDbContext(DbContextOptions<ApplicationDbContext> options) : IdentityDbContext(options)
{   
    public DbSet<Item> Items { get; set; }    
    public DbSet<Manager> Managers { get; set; }    
    public DbSet<ShoppingCart> ShoppingCarts  { get; set; }    
    public DbSet<ShoppingCartItem> ShoppingCartItems { get; set; }    
    public DbSet<StoreLocation> StoreLocations { get; set; }
    public DbSet<Store> Stores { get; set; }
    public DbSet<ShopUser> ShopUsers { get; set; }
}