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
        var response = await repository.GetAsync(
            selector: x => x,
            predicate: x => x.Id == id
        );

        if (response == null)
        {
            throw new InvalidOperationException($"Consultation with Id {id} not found");
        }

        return response;
    }

    public async Task<List<Consultation>> GetAllAsync(string? roomName)
    {
        return await repository.GetAllAsync(
            selector: x => x,
            include: x => x.Include(y => y.Room), // todo: dali treba vaka?
            predicate: x => roomName == null || x.Room.Name.Contains(roomName)
        );
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
        consultation.StartTime = dto.StartTime;
        consultation.EndTime = dto.EndTime;
        consultation.RoomId = dto.RoomId;
        return await repository.UpdateAsync(consultation);
    }

    public async Task<Consultation> DeleteByIdAsync(Guid id)
    {
        var consultation = await GetByIdNotNullAsync(id);
        return await repository.DeleteAsync(consultation);
    }

    public async Task<PaginatedResult<Consultation>> GetPagedAsync(int pageNumber, int pageSize)
    {
        
        // TODO
        var r =  await repository.GetAllPagedAsync(
            selector: x => x,
            pageNumber: pageNumber,
            pageSize: pageSize,
            include: x => x
                .Include(c => c.Room)
                .Include(c => c.Attendances)
                .ThenInclude(a => a.User),
            orderBy: x => x.OrderBy(y => y.StartTime),
            asNoTracking: true // todo: sto pravi ova??
        );
        return r;
    }
}