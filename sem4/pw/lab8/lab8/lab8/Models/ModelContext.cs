using Microsoft.EntityFrameworkCore;
using lab8.Models;

namespace lab8.Models
{
    public class ModelContext : DbContext
    {
        public DbSet<User> Users { get; set; }
        public DbSet<Document> Documents { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseMySQL("server=localhost;database=examen;user=root;password=supercool");
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            modelBuilder.Entity<User>(entity =>
            {
                entity.HasKey(e => e.Id);
                entity.Property(e => e.Username).IsRequired();
                entity.Property(e => e.Password).IsRequired();
            });

            modelBuilder.Entity<Document>(entity =>
            {
                entity.HasKey(e => e.Id);
                entity.Property(e => e.Title).IsRequired();
                entity.Property(e => e.FileUrl).IsRequired();
                entity.Property(e => e.Extension).IsRequired();
                entity.Property(e => e.Type).IsRequired();
                entity.HasOne(e => e.Author).WithMany(e => e.Documents).HasForeignKey(e => e.AuthorId);
            });
        }

        public DbSet<lab8.Models.Document> Document { get; set; }
    }
}
