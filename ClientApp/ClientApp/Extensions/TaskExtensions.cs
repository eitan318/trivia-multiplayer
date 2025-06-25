using System;
using System.Threading.Tasks;

namespace ClientApp.Extensions 
{
    public static class TaskExtensions
    {
        public static async void FireAndForgetSafeAsync(this Task task, Action<Exception> onException = null)
        {
            try
            {
                await task;
            }
            catch (Exception ex)
            {
                onException?.Invoke(ex);
            }
        }
    }
}
