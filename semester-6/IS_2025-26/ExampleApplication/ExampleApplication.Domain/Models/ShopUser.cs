using Microsoft.AspNetCore.Identity;

namespace ExampleApplication.Domain.Models;

public class ShopUser : IdentityUser
{
    public required string FirstName { get; set; }
    public required string LastName { get; set; }
}