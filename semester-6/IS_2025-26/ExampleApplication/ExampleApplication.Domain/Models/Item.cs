using ExampleApplication.Domain.Common;

namespace ExampleApplication.Domain.Models;

public class Item : BaseEntity
{
    public string? Name { get; set; }
    public int Quantity { get; set; }
    public bool Available { get; set; }

    public override string ToString()
    {
        return $"{Name} - {Quantity} - {Available}";
    }
}