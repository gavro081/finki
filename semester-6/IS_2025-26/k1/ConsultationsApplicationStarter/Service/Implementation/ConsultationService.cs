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
        var response = await repository.GetAsync(selector: x => x, predicate: x => x.Id == id);
        if (response == null)
        {
            throw new InvalidOperationException($"User with id:{id} doesn't exist");
        }

        return response;
    }

    public async Task<Consultation?> GetByIdAsync(Guid id)
    {
        return await repository.GetAsync(selector: x => x, predicate: x => x.Id == id);
    }

    public async Task<List<Consultation>> GetAllAsync(string? roomName, DateOnly? date)
    {
        return await repository.GetAllAsync(
            selector: x => x, 
            predicate: x => 
                (roomName == null || x.Room.Name.Contains(roomName)) && 
                ((date == null) || DateOnly.FromDateTime(x.StartTime) == date));
    }

    public async Task<Consultation> CreateAsync(DateTime startTime, DateTime endTime, Guid roomId)
    {
        var cons = new Consultation
        {
            StartTime = startTime,
            EndTime = endTime,
            RoomId = roomId,
            RegisteredStudents = 0
        };

        return await repository.InsertAsync(cons);
    }

    public async Task<Consultation> UpdateAsync(Guid id, DateTime startTime, DateTime endTime, Guid roomId)
    {
        var cons = await GetByIdNotNullAsync(id);
        if (cons.RegisteredStudents != 0)
        {
            throw new InvalidOperationException("cannot update. students already registered");
        }
        cons.RoomId = roomId;
        cons.StartTime = startTime;
        cons.EndTime = endTime;
        return await repository.UpdateAsync(cons);
    }

    public async Task<Consultation> DeleteByIdAsync(Guid id)
    {
        var cons = await GetByIdNotNullAsync(id);
        if (cons.RegisteredStudents != 0)
            throw new InvalidOperationException("cannot delete cons with registered students");
        
        return await repository.DeleteAsync(cons);
    }

    public async Task<PaginatedResult<Consultation>> GetPagedAsync(int pageNumber, int pageSize)
    {
        if (pageNumber < 0) pageNumber = 0;
        if (pageSize > 100) pageSize = 100;
        if (pageSize < 0) pageSize = 10;
        
        return await repository.GetAllPagedAsync(
            selector: x => x,
            include: x => x
                    .Include(c => c.Room)
                    .Include(c => c.Attendances)
                    .ThenInclude(a => a.User),
            pageNumber: pageNumber,
            pageSize: pageSize,
            asNoTracking: true
        );
    }

    public async Task DecrementNumberOfStudentsAsync(Guid id)
    {
        var response = await GetByIdNotNullAsync(id);
        response.RegisteredStudents--;
        await repository.UpdateAsync(response);
    }
    public async Task IncrementNumberOfStudentsAsync(Guid id)
    {
        var response = await GetByIdNotNullAsync(id);
        response.RegisteredStudents++;
        await repository.UpdateAsync(response);
    }
}