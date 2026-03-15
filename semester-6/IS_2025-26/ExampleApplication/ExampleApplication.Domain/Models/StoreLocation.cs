using ExampleApplication.Domain.Common;
using ExampleApplication.Domain.Enums;

namespace ExampleApplication.Domain.Models;

public class StoreLocation : BaseEntity
{
    public string LocationName { get; set; } = string.Empty;
    public StoreStatus StoreStatus { get; set; }
    
    public Guid StoreId { get; set; }
    public Store Store { get; set; } = null!;
    
    public Guid ManagerId { get; set; }
    public Manager Manager { get; set; } = null!;
}