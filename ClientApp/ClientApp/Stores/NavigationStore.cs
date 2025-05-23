using ClientApp.ViewModels;
using System;
using System.Collections.Generic;

namespace ClientApp.Stores
{
    public class NavigationStore : StoreBase
    {
        private readonly Stack<ViewModelBase> _navigationHistory = new();
        private ViewModelBase _currentViewModel;

        public bool CanGoBack()
        {
            return this._navigationHistory.Count > 0;
        }
        public void GoBack()
        {
            if (CanGoBack())
            {
                _currentViewModel = _navigationHistory.Pop();
                CurrentViewModelChanged?.Invoke();
            }
        }

        public ViewModelBase CurrentViewModel
        {
            get => _currentViewModel;
            set
            {
                if (_currentViewModel != null)
                {
                    _navigationHistory.Push(_currentViewModel);
                }
                _currentViewModel = value;
                CurrentViewModelChanged?.Invoke();
            }
        }

        public event Action CurrentViewModelChanged;
    }
}
