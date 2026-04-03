using Domain.Models;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;

namespace Repository;

public class ApplicationDbContext(DbContextOptions<ApplicationDbContext> options) : IdentityDbContext<IdentityUser>(options)
{
    public DbSet<Consultation> Consultations { get; set; }
    public DbSet<Attendance> Attendances { get; set; }
    public DbSet<Holds> Holds { get; set; }
    public DbSet<Room> Rooms { get; set; }
}