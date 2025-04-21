using ClientApp.Commands;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace ClientApp.ViewModels.ForgotPassword
{
    class CodeStepViewModel : BaseViewModel
    {
        private readonly ForgotPasswordViewModel _parent;

        private string _errorMessage;
        public string ErrorMessage
        {
            get => _errorMessage;
            set { _errorMessage = value; OnPropertyChanged(); }
        }

        public ObservableCollection<CodeBox> CodeBoxes { get; set; }

        public string TargetEmailCode { get; set; }

        public string Username {  get; set; }
        public RelayCommand SubmitCodeCommand { get; }
        public RelayCommand RetryCommand { get; }
        public CodeStepViewModel(ForgotPasswordViewModel parent)
        {
            this._parent = parent;
            // Initialize 6 code boxes
            CodeBoxes = new ObservableCollection<CodeBox>(
                Enumerable.Range(0, 6).Select(_ => new CodeBox()));

            // Setup command
            SubmitCodeCommand = new RelayCommand(SubmitCode);
            RetryCommand = new RelayCommand(Retry);
        }

        private void SubmitCode()
        {
            // Concatenate all values and process the code
            var code = string.Concat(CodeBoxes.Select(box => box.Value));
            if (code != this.TargetEmailCode)
            {
                ErrorMessage = "Wrong code";
                return;
            }
            _parent.GoToResetPasswordStep(Username);
        }

        private void Retry()
        {
            _parent.GoToEmailStep();
        }



    }



    public class CodeBox : BaseViewModel
    {
        private string _value;
        public string Value
        {
            get => _value;
            set { _value = value; OnPropertyChanged(); }
        }
    }
}
