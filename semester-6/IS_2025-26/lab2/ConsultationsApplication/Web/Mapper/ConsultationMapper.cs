using Domain.Dto;
using Domain.Models;
using Service.Interface;
using Web.Extensions;
using Web.Request;
using Web.Response;

namespace Web.Mapper;

public class ConsultationMapper(IConsultationService consultationService)
{
    public async Task<ConsultationResponse> GetByIdNotNullAsync(Guid id)
    {
        var result = await consultationService.GetByIdNotNullAsync(id);
        return result.ToResponse();
    }
    
    public async Task<List<ConsultationResponse>> GetAllAsync(string? dateAfter)
    {
        var result = await consultationService.GetAllAsync(dateAfter);
        return result.ToResponse();
    }

    public async Task<ConsultationResponse> CreateAsync(ConsultationRequest request)
    {
        var dto = request.toDto();
        var result = await consultationService.CreateAsync(dto);
        return result.ToResponse();
    }

    public async Task<ConsultationResponse> UpdateAsync(Guid id, ConsultationRequest request)
    {
        var dto = request.toDto();
        var result = await consultationService.UpdateAsync(id, dto);
        return result.ToResponse();
    }
    
    // Task<Consultation> DeleteByIdAsync(Guid id);
    public async Task<ConsultationResponse> DeleteByIdAsync(Guid id)
    {
        var resut = await consultationService.DeleteByIdAsync(id);
        return resut.ToResponse();
    }
    
    // public async 

    public async Task<PaginatedResponse<ConsultationResponse>> GetPagedAsync(PaginatedRequest request)
    {
        var result = await consultationService.GetPagedAsync(request.PageNumber, request.PageSize);
        return result.ToPaginatedResponse(e => e.ToResponse());

    }
}