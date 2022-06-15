using System;
using System.IO;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Extensions.Http;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;
using System.Collections.Generic;

namespace HocEcho
{
    public static class HttpTriggerHoc
    {
        private static Dictionary<string, string> _echo = new Dictionary<string, string>();

        [FunctionName("Echo")]
        public static async Task<IActionResult> Run(
            [HttpTrigger(AuthorizationLevel.Function, "get","post" , Route = null)] HttpRequest req, ILogger log)
        {
            log.LogInformation("Hoc Called");

            string name = req.Query["name"];
            string value = req.Query["value"];

            //validate parameters
            if(!string.IsNullOrWhiteSpace(value) && value.Length>200)
            {
                return new BadRequestObjectResult("Value is too long");
            }

            // sanity check the input
            if(string.IsNullOrEmpty(name))
            {
                log.LogInformation("Bad request: name is empty");
                return new BadRequestObjectResult("Please pass a name and value on the query string or in the request body");
            }

            // if the dictionary doesn't have the key, add it
            if (!_echo.ContainsKey(name))
            {   
                log.LogInformation("KEY NOT FOUND: " + name);
                _echo.Add(name, value??"empty"); 
                log.LogInformation("KEY ADDED: " + name);
                return new OkObjectResult("Key added");
            }

            // if the value is present update the key
            if(!string.IsNullOrEmpty(value))
            {
                _echo[name] = value;
                log.LogInformation("KEY UPDATED: " + name);
                return new OkObjectResult("Key updated");
            }
            
           
            log.LogInformation("GET: " + name + "=" + _echo[name]);
            return new OkObjectResult(_echo[name]);
        
        }
        
    }
}
