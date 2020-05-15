using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Runtime.CompilerServices;
using lab8.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace lab8.Controllers
{
    [Route("api/download")]
    [ApiController]
    [Authorize]
    public class DownloadController : ControllerBase
    {
        private readonly ModelContext _context;

        public DownloadController(ModelContext context)
        {
            _context = context;
        }

        [HttpGet]
        public HttpResponseMessage GetDocument([FromQuery(Name = "id")] int id)
        {
            Document doc = _context.Document.First(doc => doc.Id == id);
            HttpResponseMessage result;
            if (doc == null)
            {
                result = new HttpResponseMessage(HttpStatusCode.BadRequest);
                return result;
            }
            string filepath = doc.FileUrl;
            result = new HttpResponseMessage(HttpStatusCode.OK);
            var stream = new FileStream(filepath, FileMode.Open, FileAccess.Read);
            result.Content = new StreamContent(stream);
            result.Content.Headers.ContentDisposition = new ContentDispositionHeaderValue("attachment")
            {
                FileName = filepath.Substring(7)
            };
            result.Content.Headers.ContentType = new MediaTypeHeaderValue("application/octet-stream");
            return result;
        }
    }
}