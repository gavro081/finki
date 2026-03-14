using ExampleApplication.Domain.Models;
using ExampleApplication.Repository;
using ExampleApplication.Service.Interface;

namespace ExampleApplication.Service.Implementation;

public class ItemService : IItemService
{
    private readonly IRepository<Item> _itemRepository;

    public ItemService(IRepository<Item> itemRepository)
    {
        _itemRepository = itemRepository;
    }
    
    public List<Item> GetAll()
    {
        return _itemRepository.GetAll(selector: item => item).ToList();
    }

    public Item? GetById(Guid id)
    {
        return _itemRepository.Get(selector: x => x, predicate: x => x.Id == id);
    }

    public Item Update(Item item)
    {
        return _itemRepository.Update(item);
    }

    public Item DeleteById(Guid guid)
    {
        var entity = _itemRepository.Get(selector:x=>x, predicate:x=>x.Id == guid);
        return _itemRepository.Delete(entity!);
    }

    public Item Add(Item item)
    {
        item.Id = Guid.NewGuid();
        return _itemRepository.Insert(item);
    }
}