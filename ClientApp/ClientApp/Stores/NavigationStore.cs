using ClientApp.ViewModels;
using System;
using System.Collections.Generic;
using System.ComponentModel;

namespace ClientApp.Stores
{
    public class NavigationStore : StoreBase 
    {
        private readonly Stack<ScreenViewModelBase> _navigationHistory = new();
        private ScreenViewModelBase _currentViewModel;

        public bool CanGoBack() => _navigationHistory.Count > 0;

        public void GoBack()
        {
            if (CanGoBack())
            {
                CurrentViewModel = _navigationHistory.Peek();
            }
        }

        public ScreenViewModelBase CurrentViewModel
        {
            get => _currentViewModel;
            set
            {
                if (_currentViewModel != null)
                {
                    if (_navigationHistory.Contains(value))
                    {
                        // Remove all view models after the existing one in the stack
                        while (_navigationHistory.Pop() != value) { }
                    }
                    else
                    {
                        // Push the current view model onto the stack
                        _navigationHistory.Push(_currentViewModel);
                    }
                }

                _currentViewModel?.OnNavigatedAway();
                _currentViewModel = value;
                _currentViewModel?.OnNavigatedTo();

                OnPropertyChanged(nameof(CurrentViewModel));
                CurrentViewModelChanged?.Invoke();

            }
        }

        
        public event Action CurrentViewModelChanged;
    }
}
