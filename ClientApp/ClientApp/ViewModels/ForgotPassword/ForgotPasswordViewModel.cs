namespace ClientApp.ViewModels.ForgotPassword
{
    /// <summary>
    /// ViewModel that manages the steps for the forgot password process. It coordinates the navigation 
    /// between the EmailStep, CodeStep, and ResetPasswordStep, allowing users to recover their password.
    /// </summary>
    class ForgotPasswordViewModel : BaseViewModel
    {
        /// <summary>
        /// Initializes the ViewModel, setting up the steps and starting with the EmailStep by default.
        /// </summary>
        private ForgotPasswordViewModel()
        {
            EmailStep = new EmailStepViewModel(this);
            CodeStep = new CodeStepViewModel(this);
            ResetPasswordStep = new ResetPasswordStepViewModel();
            CurrentStep = EmailStep; // Start with the EmailStep by default
        }

        /// <summary>
        /// Singleton instance for the ForgotPasswordViewModel. Ensures that only one instance is created.
        /// </summary>
        /// <returns>The singleton instance of the ForgotPasswordViewModel.</returns>
        public static ForgotPasswordViewModel Instance()
        {
            return GetInstance(() => new ForgotPasswordViewModel());
        }

        /// <summary>
        /// The current step in the forgot password process (Email, Code, or ResetPassword).
        /// </summary>
        private object _currentStep;

        /// <summary>
        /// Gets or sets the current step in the forgot password process.
        /// </summary>
        public object CurrentStep
        {
            get => _currentStep;
            private set { _currentStep = value; OnPropertyChanged(); }
        }

        /// <summary>
        /// The ViewModel for the email input step in the forgot password process.
        /// </summary>
        public EmailStepViewModel EmailStep { get; }

        /// <summary>
        /// The ViewModel for the code input step in the forgot password process.
        /// </summary>
        public CodeStepViewModel CodeStep { get; }

        /// <summary>
        /// The ViewModel for the reset password step in the forgot password process.
        /// </summary>
        public ResetPasswordStepViewModel ResetPasswordStep { get; }

        /// <summary>
        /// Navigates to the code input step, passing the target email code and username for validation.
        /// </summary>
        /// <param name="targetEmailCode">The code that was sent to the user's email for validation.</param>
        /// <param name="email">The email associated with the password reset request.</param>
        public void GoToCodeStep(string email)
        {
            CodeStep.Email = email;
            CurrentStep = CodeStep;
        }

        /// <summary>
        /// Navigates back to the email input step for the user to re-enter their email.
        /// </summary>
        public void GoToEmailStep()
        {
            CurrentStep = EmailStep;
        }

        /// <summary>
        /// Navigates to the reset password step, passing the username to reset the password.
        /// </summary>
        /// <param name="email">The email associated with the account that needs a password reset.</param>
        public void GoToResetPasswordStep(string email, string tocken)
        {
            ResetPasswordStep.Tocken = tocken;
            ResetPasswordStep.Email = email;
            CurrentStep = ResetPasswordStep;
        }
    }
}
