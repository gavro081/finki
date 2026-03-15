using ExampleApplication.Domain.Common;

namespace ExampleApplication.Domain.Models;

public class ShoppingCart : BaseEntity
{
    public string? Name { get; set; }
    public DateTime CreatedAt { get; set; }
    
    public Guid StoreLocationId { get; set; }
    public StoreLocation StoreLocation { get; set; } = null!;
    
    public string UserId { get; set; }
    public ShopUser User { get; set; }
}