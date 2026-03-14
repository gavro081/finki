using ExampleApplication.Domain.Models;
using ExampleApplication.Service.Interface;
using Microsoft.AspNetCore.Mvc;

namespace ExampleApplication.Web.Controllers;
public class ItemsController : Controller
{
    private readonly IItemService _itemService;

    public ItemsController(IItemService itemService)
    {
        _itemService = itemService;
    }

    // GET Items
    public IActionResult Index()
    {
        return View(_itemService.GetAll());
    }
    
    // GET Items/Details 
    public IActionResult Details(Guid? id)
    {
        if (id == null)
        {
            return NotFound();
        }

        var item = _itemService.GetById(id.Value);
        if (item == null)
        {
            return NotFound();
        }

        return View(item);
    }

    // GET Items/Create
    public IActionResult Create()
    {
        return View();
    }

    
    // POST Items/Create
    [HttpPost]
    [ValidateAntiForgeryToken]
    public IActionResult Create([Bind("Id,Name,Quantity,Available")] Item item)
    {
        if (ModelState.IsValid)
        {
            _itemService.Add(item);
            return RedirectToAction(nameof(Index));
        }

        return View(item);
    }
    
    // GET Items/Edit/2
    public IActionResult Edit(Guid? id)
    {
        if (id == null)
        {
            return NotFound();
        }

        var item = _itemService.GetById(id.Value);
        if (item == null)
        {
            return NotFound();
        }

        return View(item);
    }
    
    // POST Items/Edit/2
    [HttpPost]
    [ValidateAntiForgeryToken]
    public IActionResult Edit(Guid id, [Bind("Id,Name,Quantity,Available")] Item item)
    {
        if (id != item.Id)
        {
            return NotFound();
        }
        
        if (ModelState.IsValid)
        {
            _itemService.Update(item);
            return RedirectToAction(nameof(Index));
        }

        return View(item);
    }
    
    // GET Items/Delete/3
    public IActionResult Delete(Guid? id)
    {
        if (id == null)
        {
            return NotFound();
        }

        var item = _itemService.GetById(id.Value);
        if (item == null)
        {
            return NotFound();
        }
        Console.WriteLine(item);

        return View(item);
    }


    // POST Products/Delete/3
    [HttpPost, ActionName("Delete")]
    [ValidateAntiForgeryToken]
    public IActionResult Delete(Guid id)
    {
        _itemService.DeleteById(id);
        return RedirectToAction(nameof(Index));
    }
}