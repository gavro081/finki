using ExampleApplication.Domain.Common;

namespace ExampleApplication.Domain.Models;

public class Person : BaseEntity
{
    public string? Name { get; set; }
    public int Age { get; set; }
}