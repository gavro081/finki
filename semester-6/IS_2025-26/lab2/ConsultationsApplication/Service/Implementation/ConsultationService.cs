using Domain.Dto;
using Domain.Models;
using Microsoft.EntityFrameworkCore;
using Repository.Interface;
using Service.Interface;

namespace Service.Implementation;

public class ConsultationService(IRepository<Consultation> repository) : IConsultationService
{
    public async Task<Consultation> GetByIdNotNullAsync(Guid id)
    {
        var result = await repository.GetAsync(
            selector: x => x,
            predicate: x => x.Id == id);

        return result ?? throw new InvalidOperationException($"Consultation with id {id}");
    }

    public async Task<List<Consultation>> GetAllAsync(string? roomName)
    {
        var result = await repository.GetAllAsync(
            selector: x => x,
            include: x => x.Include(y => y.Room),
            predicate: roomName == null ? null : x => x.Room.Name == roomName
        );
        
        return result.ToList();
    }

    public async Task<Consultation> CreateAsync(ConsultationDto dto)
    {
        var consultation = new Consultation
        {
            StartTime = dto.StartTime,
            EndTime = dto.EndTime,
            RoomId = dto.RoomId,
        };

        return await repository.InsertAsync(consultation);
    }

    public async Task<Consultation> UpdateAsync(Guid id, ConsultationDto dto)
    {
        var consultation = await GetByIdNotNullAsync(id);
        consultation.RoomId = dto.RoomId;
        consultation.StartTime = dto.StartTime;
        consultation.EndTime = dto.EndTime;
        return await repository.UpdateAsync(consultation);
    }

    public async Task<Consultation> DeleteByIdAsync(Guid id)
    {
        var consultation = await GetByIdNotNullAsync(id);
        return await repository.DeleteAsync(consultation);
    }

    public async Task<PaginatedResult<Consultation>> GetPagedAsync(int pageNumber, int pageSize)
    {
        return await repository.GetAllPagedAsync(
            selector: x => x,
            pageNumber: pageNumber,
            pageSize: pageSize,
            include: x => x.Include(y => y.Attendances),
            orderBy: x => x.OrderBy(e => e.StartTime),
            asNoTracking: true);
    }
}