using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Caching.Distributed;
using System;

namespace MyWebApp
{
    public class Startup
    {
        public void ConfigureServices(IServiceCollection services)
        {
            // Set up the Redis cache
            services.AddStackExchangeRedisCache(options =>
            {
                options.Configuration = "redis:6379";
            });
        }

        public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
        {
            app.UseRouting();

            app.UseEndpoints(endpoints =>
            {
                endpoints.MapGet("/", async context =>
                {
                    var cache = context.RequestServices.GetRequiredService<IDistributedCache>();

                    // Key for cached data
                    string cacheKey = "latestData";
                    string data = await cache.GetStringAsync(cacheKey);

                    if (string.IsNullOrEmpty(data))
                    {
                        // Simulate data fetching
                        data = $"Data fetched at {DateTime.Now}";

                        // Cache the data with an expiration time
                        var cacheEntryOptions = new DistributedCacheEntryOptions()
                            .SetSlidingExpiration(TimeSpan.FromSeconds(30)); // Cache expires after 30 seconds
                        await cache.SetStringAsync(cacheKey, data, cacheEntryOptions);

                        data = $"Fetched new: {data}";
                    }
                    else
                    {
                        data = $"Fetched from cache: {data}";
                    }

                    await context.Response.WriteAsync(data);
                });
            });
        }
    }
}
