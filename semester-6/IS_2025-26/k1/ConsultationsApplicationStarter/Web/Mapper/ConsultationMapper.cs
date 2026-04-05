using Domain.Models;
using Service.Interface;
using Web.Extensions;
using Web.Request;
using Web.Response;

namespace Web.Mapper;

public class ConsultationMapper(IConsultationService service)
{
    // GetAllAsync(roomNumber?, date?)
    public async Task<List<ConsultationsResponse>> GetAllAsync(string? roomName, DateOnly? date)
    {
        var res = await service.GetAllAsync(roomName, date);
        return res.ToResponse();
    }
    // InsertAsync(request) каде што request ги има соодветните параметри како што е наведено погоре
    public async Task<BasicConsultationsResponse> InsertAsync(ConsultationRequest request)
    {
        var res = await service.CreateAsync(request.StartTime, request.EndTime, request.RoomId);
        return res.ToBasicResponse();
    }
    
    // UpdateAsync(id, request) каде што request ги има соодветните параметри како што е наведено погоре
    public async Task<BasicConsultationsResponse> UpdateAsync(Guid id, ConsultationRequest request)
    {
        var res = await service.UpdateAsync(id, request.StartTime, request.EndTime, request.RoomId);
        return res.ToBasicResponse();
    }
    // DeleteAsync(id)
    public async Task<BasicConsultationsResponse> DeleteAsync(Guid id)
    {
        var res = await service.DeleteByIdAsync(id);
        return res.ToBasicResponse();
    }

    public async Task<PaginatedResponse<ConsultationsResponse>> GetAllPaged(PaginatedRequest request)
    {
        var res = await service.GetPagedAsync(request.PageNumber, request.PageSize);
        return res.ToPaginatedResponse(x => x.ToResponse());
    }
}