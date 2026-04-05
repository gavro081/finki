using Microsoft.AspNetCore.Mvc;
using Web.Mapper;
using Web.Request;

namespace Web.Controllers;

[Route("api/[controller]")]
[ApiController]
public class AttendanceController(AttendanceMapper mapper) : ControllerBase
{
    [HttpPost("register")]
    public async Task<IActionResult> Register([FromBody]AttendanceRequest request)
    {
        var res = await mapper.RegisterAsync(request);
        return Ok(res);
    }
    
    [HttpDelete("{id}")]
    public async Task<IActionResult> Delete([FromRoute] Guid id)
    {
        await mapper.DeleteAsync(id);
        return Ok();
    }

    [HttpGet("consultation/{consultationId}")]
    public async Task<IActionResult> GetByConsultationId([FromRoute] Guid consultationId)
    {
        var res = await mapper.GetAllByConsultationIdAsync(consultationId);
        return Ok(res);
    }

    [HttpPatch("{id}/mark-as-absent")]
    public async Task<IActionResult> MarkAsAbsent([FromRoute] Guid id)
    {
        await mapper.MarkAsAbsentAsync(id);
        return Ok();
    }

    [HttpPost("{id}/cancelation-reason")]
    public async Task<IActionResult> UploadImageByIdAsync([FromRoute] Guid id, [FromForm] IFormFile file)
    {
        var res = await mapper.UploadReasonByIdInFileSystemAsync(id, file);
        return Ok(res);
    }
}