using lab8.DTOs;
using System;
using System.IO;
using System.Linq;

namespace lab8.Models
{
    public class Document
    {
        public Document() { }

        private static string RandomString(int length)
        {
            Random random = new Random();
            const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
            return new string(Enumerable.Repeat(chars, length)
              .Select(s => s[random.Next(s.Length)]).ToArray());
        }

        public Document(DocumentInputDTO documentDTO)
        {
            this.Title = documentDTO.Title;
            byte[] content = Convert.FromBase64String(documentDTO.File);
            string filepath = $"Files/{RandomString(20)}.{documentDTO.Extension.ToLower()}";
            File.WriteAllBytes(filepath, content);
            this.Extension = documentDTO.Extension;
            this.FileUrl = filepath;
            this.Type = documentDTO.Type;
        }

        public int Id { get; set; }
        public string Title { get; set; }
        public string FileUrl { get; set; }

        public string Extension { get; set; }

        public string Type { get; set; }

        public long AuthorId { get; set; }

        public User Author { get; set; }
    }
}
