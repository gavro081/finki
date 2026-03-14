using ExampleApplication.Domain.Models;
using Microsoft.EntityFrameworkCore;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;

namespace ExampleApplication.Repository;

public class ApplicationDbContext(DbContextOptions<ApplicationDbContext> options) : IdentityDbContext(options)
{   
    public DbSet<Person> Persons { get; set; }    
    public DbSet<Item> Items { get; set; }    
}