using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Web.Mapper;
using Web.Request;

namespace Web.Controllers;


[Route("api/[controller]")]
[ApiController]
public class ConsultationsController(ConsultationMapper consultationsMapper) : ControllerBase
{
    [HttpGet("{id}")]
    public async Task<IActionResult> GetById([FromRoute] Guid id)
    {
        var res = await consultationsMapper.GetByIdNotNullAsync(id);
        return Ok(res);
    }

    [HttpGet]
    public async Task<IActionResult> GetAll([FromQuery] string? roomName)
    {
        var res = await consultationsMapper.GetAllAsync(roomName);
        return Ok(res);
    }

    [HttpGet("paged")]
    public async Task<IActionResult> GetPaged([FromQuery] PaginatedRequest request)
    {
        var res = await consultationsMapper.GetPagedAsync(request);
        return Ok(res);
    }

    [HttpPost]
    [Authorize]
    public async Task<IActionResult> Create([FromBody] ConsultationRequest request)
    {
        var res = await consultationsMapper.CreateAsync(request);
        return Ok(res);
    }

    [HttpPut("{id}")]
    [Authorize]
    public async Task<IActionResult> Update([FromRoute] Guid id, [FromBody] ConsultationRequest req)
    {
        var res = await consultationsMapper.UpdateAsync(id, req);
        return Ok(res);
    }

    [HttpDelete("{id}")]
    [Authorize]
    public async Task<IActionResult> Delete([FromRoute] Guid id)
    {
        var res = await consultationsMapper.DeleteByIdAsync(id);
        return Ok(res);
    }
}