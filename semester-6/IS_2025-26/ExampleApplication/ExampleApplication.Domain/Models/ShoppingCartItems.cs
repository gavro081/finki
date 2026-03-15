using ExampleApplication.Domain.Common;

namespace ExampleApplication.Domain.Models;

public class ShoppingCartItem : BaseEntity
{
    public int Quantity { get; set; } = 1;
    public DateTime AddedAt { get; set; }
    
    public Guid ShoppingCartId { get; set; }
    public ShoppingCart ShoppingCart { get; set; } = null!;
    
    public Guid ItemId { get; set; }
    public Item Item { get; set; } = null!;
}