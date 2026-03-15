using ExampleApplication.Domain.Common;

namespace ExampleApplication.Domain.Models;

public class Manager : BaseEntity
{
    public required string FirstName { get; set; }
    public required string LastName { get; set; }
    public required double Salary { get; set; }
    
    public StoreLocation? StoreLocation { get; set; }
}