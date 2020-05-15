using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using lab8.Models;
using Microsoft.AspNetCore.Authorization;
using lab8.DTOs;
using System.IdentityModel.Tokens.Jwt;

namespace lab8.Controllers
{
    [Route("api/documents")]
    [ApiController]
    [Authorize]
    public class DocumentsController : ControllerBase
    {
        private readonly ModelContext _context;

        private User getUserFromJwt()
        {
            string jwt = ((string)Request.Headers["Authorization"]).Substring(7);
            string username = new JwtSecurityTokenHandler().ReadJwtToken(jwt).Claims.First(c => c.Type == "user").Value;
            return _context.Users.First(u => u.Username == username);
        }

        public DocumentsController(ModelContext context)
        {
            _context = context;
        }

        // GET: api/documents
        [HttpGet]
        public async Task<ActionResult<IEnumerable<DocumentOutputDTO>>> GetDocument()
        {
            IEnumerable<Document> documents = await _context.Documents.ToListAsync();
            foreach(Document doc in documents)
            {
                doc.Author = _context.Users.First(u => u.Id == doc.AuthorId);
            }
            return await _context.Document.Select(doc => new DocumentOutputDTO(doc)).ToListAsync();
        }

        // GET: api/documents/5
        [HttpGet("{id}")]
        public async Task<ActionResult<DocumentOutputDTO>> GetDocument(int id)
        {
            var document = await _context.Document.FindAsync(id);
            if (document == null)
            {
                return NotFound();
            }
            document.Author = _context.Users.First(u => u.Id == document.AuthorId);

            return new DocumentOutputDTO(document);
        }

        // PUT: api/documents/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for
        // more details, see https://go.microsoft.com/fwlink/?linkid=2123754.
        [HttpPut("{id}")]
        public async Task<IActionResult> PutDocument(int id, DocumentInputDTO documentDTO)
        {
            Document document = new Document(documentDTO);
            document.Id = id;
            document.Author = getUserFromJwt();

            _context.Entry(document).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!DocumentExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }
            return NoContent();
        }

        // POST: api/documents
        // To protect from overposting attacks, enable the specific properties you want to bind to, for
        // more details, see https://go.microsoft.com/fwlink/?linkid=2123754.
        [HttpPost]
        public async Task<ActionResult<DocumentOutputDTO>> PostDocument(DocumentInputDTO documentDTO)
        {
            Document newDocument = new Document(documentDTO)
            {
                Author = getUserFromJwt()
            };
            _context.Document.Add(newDocument);
            await _context.SaveChangesAsync();
            return new DocumentOutputDTO(newDocument);
        }

        // DELETE: api/documents/5
        [HttpDelete("{id}")]
        public async Task<ActionResult<DocumentOutputDTO>> DeleteDocument(int id)
        {
            var document = await _context.Document.FindAsync(id);
            document.Author = _context.Users.First(u => u.Id == document.AuthorId);
            if (document == null)
            {
                return NotFound();
            }

            _context.Document.Remove(document);
            await _context.SaveChangesAsync();

            return new DocumentOutputDTO(document);
        }

        private bool DocumentExists(int id)
        {
            return _context.Document.Any(e => e.Id == id);
        }
    }
}
