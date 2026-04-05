using Service.Interface;
using Web.Extensions;
using Web.Request;
using Web.Response;

namespace Web.Mapper;

public class ConsultationMapper(IConsultationService consultationService)
{
    // Task<Consultation> GetByIdNotNullAsync(Guid id);
    public async Task<ConsultationResponse> GetByIdNotNullAsync(Guid id)
    {
        var res = await consultationService.GetByIdNotNullAsync(id);
        return res.ToResponse();
    }
    // Task<List<Consultation>> GetAllAsync(string? dateAfter);
    public async Task<List<ConsultationResponse>> GetAllAsync(string? roomName)
    {
        var res = await consultationService.GetAllAsync(roomName);
        return res.ToResponse();
    }
    // Task<Consultation> CreateAsync(ConsultationDto dto);
    public async Task<ConsultationResponse> CreateAsync(ConsultationRequest req)
    {
        var res = await consultationService.CreateAsync(req.ToDto());
        return res.ToResponse();
    }
    // Task<Consultation> UpdateAsync(Guid id, ConsultationDto dto);
    public async Task<ConsultationResponse> UpdateAsync(Guid id, ConsultationRequest req)
    {
        var res = await consultationService.UpdateAsync(id, req.ToDto());
        return res.ToResponse();
    }
    // Task<Consultation> DeleteByIdAsync(Guid id);
    public async Task<ConsultationResponse> DeleteByIdAsync(Guid id)
    {
        var res = await consultationService.DeleteByIdAsync(id);
        return res.ToResponse();
    }
    // Task<PaginatedResult<Consultation>> GetPagedAsync(int pageNumber, int pageSize);
    public async Task<PaginatedResponse<ConsultationWithAttendancesResponse>> GetPagedAsync(PaginatedRequest request)
    {
        var res = await consultationService.GetPagedAsync(request.PageNumber, request.PageSize);
        return res.ToPaginatedResponse(e => e.ToResponseWithAttendance());
    }
}