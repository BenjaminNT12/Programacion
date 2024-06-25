# Datos
debt_amount = 1900000  # Monto del préstamo en MXN
annual_interest_rate = 0.205  # Tasa de interés anual del 20.5%
loan_term_years = 6  # Plazo del préstamo en años
commission = 28500  # Comisión en MXN
opening_cost = 12550  # Costo de apertura en MXN
equity_value = 250000  # Valor de la empresa en MXN
required_return_on_equity = 0.10  # Rendimiento neto requerido del 10%
corporate_tax_rate = 0.16  # Tasa impositiva corporativa del 16%

# Costo total inicial del préstamo (incluyendo comisión y apertura)
total_loan_cost = debt_amount + commission + opening_cost

# Cálculo del costo anual de la deuda
interest_payment_per_year = debt_amount * annual_interest_rate

# Valor presente del costo total del préstamo
total_interest_payments = interest_payment_per_year * loan_term_years
total_cost_of_debt = total_interest_payments + commission + opening_cost
total_cost_of_debt = 2715516.33
print(f"Costo total de la deuda: {total_cost_of_debt}")
# Tasa efectiva de la deuda
effective_debt_rate = (total_cost_of_debt / debt_amount) / loan_term_years
print(f"Tasa efectiva de la deuda: {effective_debt_rate}")
# Ajuste de la tasa de la deuda por la tasa impositiva
after_tax_cost_of_debt = effective_debt_rate * (1 - corporate_tax_rate)
print(f"Ajuste de la tasa de la deuda por la tasa impositiva: {after_tax_cost_of_debt}")
# Calcular el valor de la deuda y el valor total de la empresa
total_value = debt_amount + equity_value
print(f"Calcular el valor de la deuda y el valor total de la empresa: {total_value}")
# Ponderación de la deuda y del capital propio
weight_of_debt = debt_amount / total_value
weight_of_equity = equity_value / total_value

# Cálculo del WACC
wacc = (weight_of_debt * after_tax_cost_of_debt) + (weight_of_equity * required_return_on_equity)
wacc = ((debt_amount / total_value) * (effective_debt_rate * (1 - corporate_tax_rate))) + ((equity_value / total_value) * required_return_on_equity)
print(f"({debt_amount} / {total_value}) * ({effective_debt_rate} * (1 - {corporate_tax_rate}))) + (({equity_value} / {total_value}) * {required_return_on_equity} = {wacc}")

# Resultados
print("Costo de la deuda antes de impuestos (rd):", effective_debt_rate)
print("Costo de la deuda después de impuestos (rd*(1-T)):", after_tax_cost_of_debt)
print("Ponderación de la deuda (D/V):", weight_of_debt)
print("Ponderación del capital propio (E/V):", weight_of_equity)
print("Costo promedio ponderado de capital (WACC):", wacc)
