using ExampleApplication.Domain.Models;

namespace ExampleApplication.Service.Interface;

public interface IItemService
{
    List<Item> GetAll();
    Item? GetById(Guid id);
    Item Update(Item item);
    Item DeleteById(Guid guid);
    Item Add(Item item);
}