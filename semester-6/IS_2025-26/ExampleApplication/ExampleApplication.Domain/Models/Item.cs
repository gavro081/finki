using ExampleApplication.Domain.Common;
using ExampleApplication.Domain.Enums;

namespace ExampleApplication.Domain.Models;

public class Item : BaseEntity
{
    public string? Name { get; set; }
    public bool Available { get; set; }

    public ItemPriceStatus ItemPriceStatus { get; set; } = ItemPriceStatus.RegularPrice;
    public override string ToString()
    {
        return $"{Name} - {Available}";
    }
}