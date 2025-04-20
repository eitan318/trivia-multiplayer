namespace ClientApp.ViewModels.ForgotPassword
{
    class ForgotPasswordViewModel : BaseViewModel
    {
        private ForgotPasswordViewModel()
        {
            EmailStep = new EmailStepViewModel(this);
            CodeStep = new CodeStepViewModel(this);
            ResetPasswordStep = new ResetPasswordStepViewModel();
            CurrentStep = EmailStep; // Start with the EmailStep by default
        }

        // Singleton instance
        public static ForgotPasswordViewModel Instance()
        {
            return GetInstance(() => new ForgotPasswordViewModel());
        }

        private object _currentStep;

        public object CurrentStep
        {
            get => _currentStep;
            private set => SetProperty(ref _currentStep, value);
        }

        public EmailStepViewModel EmailStep { get; }
        public CodeStepViewModel CodeStep { get; }
        public ResetPasswordStepViewModel ResetPasswordStep { get; }

        public void GoToCodeStep(string targetEmailCode, string username)
        {
            CodeStep.TargetEmailCode = targetEmailCode;
            CodeStep.Username = username;
            CurrentStep = CodeStep;
        }

        public void GoToEmailStep()
        {
            CurrentStep = EmailStep;
        }

        public void GoToResetPasswordStep(string username)
        {
            ResetPasswordStep.Username = username;
            CurrentStep = ResetPasswordStep;
        }
    }
}
