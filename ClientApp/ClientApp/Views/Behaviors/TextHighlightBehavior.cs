﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Media;
using System.Windows;

namespace ClientApp.Views.Behaviors
{
    /// <summary>
    /// Provides an attached behavior that highlights specific text within a <see cref="TextBlock"/>.
    /// </summary>
    public static class TextHighlightBehavior
    {
        /// <summary>
        /// Identifies the HighlightText attached property.
        /// </summary>
        public static readonly DependencyProperty HighlightTextProperty =
            DependencyProperty.RegisterAttached(
                "HighlightText",
                typeof(string),
                typeof(TextHighlightBehavior),
                new PropertyMetadata(string.Empty, OnHighlightTextChanged));

        /// <summary>
        /// Gets the value of the HighlightText attached property for the specified <see cref="DependencyObject"/>.
        /// </summary>
        /// <param name="obj">The object from which to read the property value.</param>
        /// <returns>The value of the HighlightText attached property.</returns>
        public static string GetHighlightText(DependencyObject obj) =>
            (string)obj.GetValue(HighlightTextProperty);

        /// <summary>
        /// Sets the value of the HighlightText attached property for the specified <see cref="DependencyObject"/>.
        /// </summary>
        /// <param name="obj">The object on which to set the property value.</param>
        /// <param name="value">The new value of the HighlightText property.</param>
        public static void SetHighlightText(DependencyObject obj, string value) =>
            obj.SetValue(HighlightTextProperty, value);

        /// <summary>
        /// Called when the HighlightText property changes. Updates the specified <see cref="TextBlock"/> to highlight matching text.
        /// </summary>
        /// <param name="d">The <see cref="DependencyObject"/> where the property change occurred.</param>
        /// <param name="e">The event arguments for the property change.</param>
        private static void OnHighlightTextChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if (d is TextBlock textBlock && e.NewValue is string query)
            {
                var fullText = textBlock.Text;
                textBlock.Inlines.Clear();

                if (!string.IsNullOrEmpty(query) && !string.IsNullOrEmpty(fullText))
                {
                    int index = fullText.IndexOf(query, StringComparison.OrdinalIgnoreCase);
                    if (index >= 0)
                    {
                        textBlock.Inlines.Add(new Run(fullText.Substring(0, index)));
                        textBlock.Inlines.Add(new Run(fullText.Substring(index, query.Length))
                        {
                            FontWeight = FontWeights.Bold,
                            Foreground = Brushes.Orange
                        });
                        textBlock.Inlines.Add(new Run(fullText.Substring(index + query.Length)));
                    }
                    else
                    {
                        textBlock.Inlines.Add(new Run(fullText));
                    }
                }
                else
                {
                    textBlock.Inlines.Add(new Run(fullText));
                }
            }
        }
    }
}

