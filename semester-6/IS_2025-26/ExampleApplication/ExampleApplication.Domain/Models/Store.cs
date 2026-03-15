using ExampleApplication.Domain.Common;

namespace ExampleApplication.Domain.Models;

public class Store : BaseEntity
{
    public required string Title { get; set; }
}