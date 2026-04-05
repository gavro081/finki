using Microsoft.AspNetCore.Mvc;
using Web.Mapper;
using Web.Request;

namespace Web.Controllers;

[Route("api/[controller]")]
[ApiController]
public class ConsultationController(ConsultationMapper mapper) : ControllerBase
{
    [HttpPost]
    public async Task<IActionResult> Create([FromBody]ConsultationRequest request)
    {
        var response = await mapper.InsertAsync(request);
        return Ok(response);
    }

    [HttpGet]
    public async Task<IActionResult> GetAll([FromQuery] string? roomName, [FromQuery] DateOnly? date)
    {
        var response = await mapper.GetAllAsync(roomName, date);
        return Ok(response);
    }

    [HttpPut("{id}")]
    public async Task<IActionResult> Update([FromRoute] Guid id, [FromBody] ConsultationRequest request)
    {
        var response = await mapper.UpdateAsync(id, request);
        return Ok(response);
    }
    
    [HttpDelete("{id}")]
    public async Task<IActionResult> Delete([FromRoute] Guid id)
    {
        await mapper.DeleteAsync(id);
        return Ok();
    }
 
    [HttpGet("paged")]
    public async Task<IActionResult> GetPaged([FromQuery]PaginatedRequest request)
    {
        var response = await mapper.GetAllPaged(request);
        return Ok(response);
    }
}