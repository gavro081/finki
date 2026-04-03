using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Web.Mapper;
using Web.Request;
using Web.Response;

namespace Web.Controllers;


[Route("api/[controller]")]
[ApiController]
public class ConsultationsController(ConsultationMapper consultationMapper) : ControllerBase
{
    [HttpGet("{id}")]
    public async Task<IActionResult> GetById([FromRoute] Guid id)
    {
        var result = await consultationMapper.GetByIdNotNullAsync(id);
        return Ok(result);
    }
    
    [HttpGet("paged")]
    public async Task<PaginatedResponse<ConsultationResponse>> Paged([FromQuery] PaginatedRequest request)
    {
        return await consultationMapper.GetPagedAsync(request);
    }
    
    [HttpPost]
    public async Task<IActionResult> Insert([FromBody] ConsultationRequest consultationRequest)
    {
        var result = await consultationMapper.CreateAsync(consultationRequest);
        return Ok(result);
    }
    
    [HttpPut("{id}")]
    [Authorize]
    public async Task<IActionResult> Update([FromRoute] Guid id, [FromBody] ConsultationRequest consultationRequest)
    {
        var result = await consultationMapper.UpdateAsync(id, consultationRequest);
        return Ok(result);
    }
    
    
    [HttpDelete("{id}")]
    [Authorize]
    public async Task<IActionResult> Delete([FromRoute] Guid id)
    {
        var result = await consultationMapper.DeleteByIdAsync(id);
        return Ok(result);
    }

}