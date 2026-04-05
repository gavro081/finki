using Service.Interface;
using Web.Extensions;
using Web.Request;
using Web.Response;

namespace Web.Mapper;

public class AttendanceMapper(IAttendanceService service, IFileUploadService fileUploadService)
{
    // RegisterAsync(request) каде што request ги има соодветните параметри како што е наведено погоре
    public async Task<AttendanceResponse> RegisterAsync(AttendanceRequest request)
    {
        var res = await service.CreateAsync(request.ToDto());
        return res.ToResponse();

    }
    // DeleteAsync(id)
    public async Task DeleteAsync(Guid id)
    {
        await service.DeleteByIdAsync(id);
    }
    // GetAllByConsultationIdAsync(id)
    public async Task<List<AttendanceResponse>> GetAllByConsultationIdAsync(Guid id)
    {
        var res = await service.GetAllByConsultationIdAsync(id);
        return res.ToResponse();

    }
    // MarkAsAbsentAsync(id)
    public async Task MarkAsAbsentAsync(Guid id)
    {
        await service.MarkAsAbsent(id);
    }
    // UploadReasonByIdInFileSystemAsync(id, file)
    public async Task<AttendanceResponse> UploadReasonByIdInFileSystemAsync(Guid id, IFormFile file)
    {
        using var ms = new MemoryStream();
        await file.CopyToAsync(ms);

        var path = await fileUploadService.UploadFileAsync(
            ms.ToArray(), file.FileName);

        var res = await service.UpdateReasonPathByIdAsync(id, path);
        return res.ToResponse();
    }
}