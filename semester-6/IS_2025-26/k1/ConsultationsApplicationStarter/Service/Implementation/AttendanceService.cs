using Domain.Dto;
using Domain.Enums;
using Domain.Models;
using Repository.Interface;
using Service.Interface;

namespace Service.Implementation;

public class AttendanceService(IRepository<Attendance> repository, IConsultationService consultationService) : IAttendanceService
{
    public async Task<Attendance> GetByIdNotNullAsync(Guid id)
    {
        var response = await repository.GetAsync(selector: x => x, predicate: x => x.Id == id);
        if (response == null)
        {
            throw new InvalidOperationException($"User with id:{id} doesn't exist");
        }

        return response;
    }

    public async Task<Attendance?> GetByIdAsync(Guid id)
    {
        return await repository.GetAsync(selector: x => x, predicate: x => x.Id == id);
    }

    public async Task<List<Attendance>> GetAllAsync(string? dateAfter)
    {
        // dali ke mi treba include?
        return await repository.GetAllAsync(selector: x => x);
    }   
    public async Task<List<Attendance>> GetAllByConsultationIdAsync(Guid id)
    {
        return await repository.GetAllAsync(selector: x => x, predicate: x => x.ConsultationId == id);
    }

    public async Task<Attendance> CreateAsync(AttendanceDto dto)
    {
        var att = new Attendance
        {
            UserId = dto.UserId,
            Comment = dto.Comment,
            ConsultationId = dto.ConsultationId,
            RoomId = dto.RoomId,
        };
        
        var response = await repository.InsertAsync(att);

        await consultationService.IncrementNumberOfStudentsAsync(dto.ConsultationId);
        
        return await GetByIdNotNullAsync(response.Id);
    }

    public async Task<Attendance> UpdateAsync(Guid id, AttendanceDto dto)
    {
        var att = await GetByIdNotNullAsync(id);
        att.UserId = dto.UserId;
        att.RoomId = dto.RoomId;
        att.ConsultationId = dto.ConsultationId;
        att.Comment = dto.Comment;
        return await repository.UpdateAsync(att);
    }

    public async Task<Attendance> DeleteByIdAsync(Guid id)
    {
        var att = await GetByIdNotNullAsync(id);
        var consultation = await consultationService.GetByIdNotNullAsync(att.ConsultationId);
        if (consultation.StartTime <= DateTime.Now.AddHours(1))
        {
            throw new InvalidOperationException("Cannot cancel less than 1 hour before start");
        }

        await consultationService.DecrementNumberOfStudentsAsync(consultation.Id);
        return await repository.DeleteAsync(att);
    }

    public async Task<PaginatedResult<Attendance>> GetPagedAsync(int pageNumber, int pageSize)
    {
        if (pageNumber < 0) pageNumber = 0;
        if (pageSize > 100) pageSize = 100;
        if (pageSize < 0) pageSize = 10;
        
        return await repository.GetAllPagedAsync(
            selector: x => x,
            pageNumber: pageNumber,
            pageSize: pageSize,
            asNoTracking: true
        );
    }

    public async Task MarkAsAbsent(Guid id)
    {
        var res = await GetByIdNotNullAsync(id);
        res.Status = Status.Absent;
        await repository.UpdateAsync(res);
    }
    
    public async Task<Attendance> UpdateReasonPathByIdAsync(Guid id, string path)
    {
        var res = await GetByIdNotNullAsync(id);
        res.CancellationReasonDocumentPath = path;
        return await repository.UpdateAsync(res);
    }
}